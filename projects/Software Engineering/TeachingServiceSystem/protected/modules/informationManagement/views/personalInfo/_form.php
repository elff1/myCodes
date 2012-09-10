<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'personal-info-form',
	'enableAjaxValidation'=>false,
	'enableClientValidation'=>true,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<p class="note">
	<?php echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); ?>
	</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'first_name'); ?>
		<?php echo $form->textField($model,'first_name',array('size'=>8,'maxlength'=>8)); ?>
		<?php echo $form->error($model,'first_name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'last_name'); ?>
		<?php echo $form->textField($model,'last_name',array('size'=>8,'maxlength'=>8)); ?>
		<?php echo $form->error($model,'last_name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'sex'); ?>
		<?php echo $form->dropDownList($model,'sex',$model->genderOptions); ?>
		<?php echo $form->error($model,'sex'); ?>
	</div>
	
	<div class="row">
		<?php echo $form->labelEx($model,'image'); ?>
		<?php echo $form->fileField($model,'image'); ?>
		<?php echo $form->error($model,'image'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'date_of_birth'); ?>		
		<?php $this->widget('zii.widgets.jui.CJuiDatePicker', array(  

        'attribute' => 'date_of_birth',  
        'model'=>$model,
        'options' => array(
                'dateFormat' => 'yy-mm-dd',  

        ),
		));?>
		
		<?php echo $form->error($model,'date_of_birth'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'ethnic_group'); ?>
		<?php echo $form->dropDownList($model,'ethnic_group', $model->ethnicGroupList); ?>
		<?php echo $form->error($model,'ethnic_group'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'political_status'); ?>
		<?php echo $form->dropDownList($model,'political_status', $model->politicalStatusList); ?>
		<?php echo $form->error($model,'political_status'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'birth_place_city'); ?>
		<?php echo $form->dropDownList($model,'birth_place_city',$model->getCityList($model->birth_place_province)); ?>
		<?php echo $form->error($model,'birth_place_city'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'birth_place_province'); ?>
		<?php echo $form->dropDownList($model,'birth_place_province',$model->provinceList, 
		array(
			'ajax'=>array(
				'url'=>$this->createUrl('personalInfo/dynamicCity'),
				'data'=>array('pid'=>'js:this.value'),
				'update'=>'#'.CHtml::activeId($model,'birth_place_city'),
				),
			)
			
		); ?>
		<?php echo $form->error($model,'birth_place_province'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'original_residence_city'); ?>
		<?php echo $form->dropDownList($model,'original_residence_city',$model->getCityList($model->original_residence_province)); ?>
		<?php echo $form->error($model,'original_residence_city'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'original_residence_province'); ?>
		<?php echo $form->dropDownList($model,'original_residence_province',$model->provinceList, 
		array(
			'ajax'=>array(
				'url'=>$this->createUrl('personalInfo/dynamicCity'),
				'data'=>array('pid'=>'js:this.value'),
				'update'=>'#'.CHtml::activeId($model,'original_residence_city'),
				),
			)
			
		); ?>
		<?php echo $form->error($model,'original_residence_province'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'home_address'); ?>
		<?php echo $form->textField($model,'home_address',array('size'=>60,'maxlength'=>64)); ?>
		<?php echo $form->error($model,'home_address'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'home_postcode'); ?>
		<?php echo $form->textField($model,'home_postcode',array('size'=>6,'maxlength'=>6)); ?>
		<?php echo $form->error($model,'home_postcode'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'home_phone'); ?>
		<?php echo $form->textField($model,'home_phone',array('size'=>32,'maxlength'=>32)); ?>
		<?php echo $form->error($model,'home_phone'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'email'); ?>
		<?php echo $form->textField($model,'email',array('size'=>60,'maxlength'=>64)); ?>
		<?php echo $form->error($model,'email'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'phone'); ?>
		<?php echo $form->textField($model,'phone',array('size'=>32,'maxlength'=>32)); ?>
		<?php echo $form->error($model,'phone'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'identity_card_number'); ?>
		<?php echo $form->textField($model,'identity_card_number',array('size'=>18,'maxlength'=>18)); ?>
		<?php echo $form->error($model,'identity_card_number'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? InformationManagementModule::t('other','Create') : InformationManagementModule::t('other','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->