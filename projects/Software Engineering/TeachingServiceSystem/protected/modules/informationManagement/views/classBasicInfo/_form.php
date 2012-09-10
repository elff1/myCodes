<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'class-basic-info-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">
	<?php echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); ?>
	</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'name'); ?>
		<?php echo $form->textField($model,'name',array('size'=>16,'maxlength'=>16)); ?>
		<?php echo $form->error($model,'name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'grade'); ?>
		<?php echo $form->textField($model,'grade',array('size'=>4,'maxlength'=>4)); ?>
		<?php echo $form->error($model,'grade'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'tutor_id'); ?>
		<?php echo $form->textField($model,'tutor_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'tutor_id'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? InformationManagementModule::t('other','Create') : InformationManagementModule::t('other','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->