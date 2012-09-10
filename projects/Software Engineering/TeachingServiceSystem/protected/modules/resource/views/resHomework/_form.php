<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'res-homework-form',
	'enableAjaxValidation'=>false,
    'htmlOptions'=>array('enctype'=>'multipart/form-data'),
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>
    <?php echo $form->errorSummary($res_model); ?>

	<div class="row">
		<?php //echo $form->labelEx($model,'student_id'); ?>
		<?php //echo $form->textField($model,'student_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php //echo $form->error($model,'student_id'); ?>
	</div>

	<div class="row">
    <input type='hidden' name='ResHomework[hid]' value='' />
    <?php 
        if(Yii::app()->user->type == 2){
            echo $form->labelEx($model,'score'); 
            echo $form->textField($model,'score');
            echo $form->error($model,'score'); 
        }
    ?>
	</div>

	<div class="row">
		<?php //echo $form->labelEx($model,'assignment_id'); ?>
		<?php //echo $form->textField($model,'assignment_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php //echo $form->error($model,'assignment_id'); ?>
	</div>

	<div class="row">
		<?php //echo $form->labelEx($model,'teachingclass_id'); ?>
		<?php //echo $form->textField($model,'teachingclass_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php //echo $form->error($model,'teachingclass_id'); ?>
	</div>

	<div class="row">
        <?php 
            if(Yii::app()->user->type == 2){
                echo $form->labelEx($model,'comments');
                //echo $form->textField($model,'comments',array('size'=>60,'maxlength'=>1024));
                $this->widget('ext.editMe.ExtEditMe', array(
                    'model' => $model,
                    'attribute' => 'comments',
                ));
                echo $form->error($model,'comments');
            }
        ?>
	</div>


    <div class="row">
<?php
    if (Yii::app()->user->type==1) {
        echo $form->labelEx($res_model, 'path'); 
        echo $form->fileField($res_model, 'path', '');
        echo $form->error($res_model, 'path');
    }
 ?>
    </div>

    <div class="row">
<?php
    // show the name of the attachment
    if (Yii::app()->user->type==1) {
            echo $form->labelEx($res_model, 'display_name');
            echo $form->textField($res_model, 'display_name',
        array('size'=>60, 'maxlength'=>255));
            echo $form->error($res_model, 'display_name');
    }?>
    </div>

    <div class="row">
<?php
        // show attachment description
        if (Yii::app()->user->type==1) {
            echo $form->labelEx($res_model, 'description');
            echo $form->textArea($res_model, 'description', array(
                'size'=>60, 'maxlength'=>2048));
            echo $form->error($res_model, 'description'); 
        } ?>
    </div>
    

	<div class="row">
		<?php //echo $form->labelEx($model,'resource_id'); ?>
		<?php //echo $form->textField($model,'resource_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php //echo $form->error($model,'resource_id'); ?>
	</div>

	<div class="row buttons">
        <?php echo CHtml::submitButton(
    $model->isNewRecord || $res_model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->
